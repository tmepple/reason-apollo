let ste = ReasonReact.string;

module AddPerson = [%graphql
  {|
    mutation addPerson($age: Int!, $name: String!) {
        createPerson(age: $age, name: $name) {
          name
        }
      }
|}
];

let component = ReasonReact.statelessComponent("AddPerson");

module AddPersonMutation = ReasonApollo.CreateMutation(AddPerson);

let make = _children => {
  ...component,
  render: _self => {
    let addPersonMutation = AddPerson.make(~name="Steve", ~age=42, ());
    <AddPersonMutation>
      ...(
           (mutation, {result}) => {
             Js.log(result);
             <div>
               (
                 switch (result) {
                 | Called => <div> ("Called" |> ste) </div>
                 | Loading => <div> ("Loading" |> ste) </div>
                 | Error(err) => <div> ("Error" |> ste) </div>
                 | NoData => <div> ("NoData" |> ste) </div>
                 | Data(data) => <div> ("Data" |> ste) </div>
                 }
               )
               <button
                 onClick=(
                   (_) => {
                     mutation(
                       ~variables=addPersonMutation##variables,
                       ~refetchQueries=[|"getAllPersons"|],
                       (),
                     )
                     |> ignore;
                     Js.log("SEND");
                   }
                 )>
                 ("Add a person" |> ReasonReact.string)
               </button>
             </div>;
           }
         )
    </AddPersonMutation>;
  },
};
