let ste = ReasonReact.string;

module DeletePerson = [%graphql
  {|
    mutation deletePerson($id: ID!) {
        deletePerson(id: $id) {
          id
        }
      }
|}
];

let component = ReasonReact.statelessComponent("DeletePerson");

module DeletePersonMutation = ReasonApollo.CreateMutation(DeletePerson);

let make = _children => {
  ...component,
  render: _self => {
    /* pick a valid id from list returned from GetPersons query here
       "https://api.graph.cool/simple/v1/cjdgba1jw4ggk0185ig4bhpsn" and pass it to ~id variable
       */
    let deletePersonMutation = DeletePerson.make(~id="cjh94corlzfxw0118i9fchgan", ());
    <DeletePersonMutation>
      ...(
           (mutation, _) =>
             <button
               onClick=(
                 (_) => {
                   mutation(
                     ~variables=deletePersonMutation##variables,
                     ~refetchQueries=[|"getAllPersons"|],
                     (),
                   )
                   |> ignore;
                   Js.log("SEND");
                 }
               )>
               ("Delete a person" |> ReasonReact.string)
             </button>
         )
    </DeletePersonMutation>;
  },
};
